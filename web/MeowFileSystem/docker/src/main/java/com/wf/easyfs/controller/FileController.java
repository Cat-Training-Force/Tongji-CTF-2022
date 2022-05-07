package com.wf.easyfs.controller;

import net.coobird.thumbnailator.Thumbnails;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.net.URLEncoder;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * 文件服务器
 * Created by wangfan on 2018-12-24 下午 4:10.
 */
@Controller
public class FileController {
    @Value("${fs.dir}")
    private String fileDir;
    @Value("${fs.uuidName}")
    private Boolean uuidName;
    @Value("${fs.useSm}")
    private Boolean useSm;
    @Value("${fs.useNginx}")
    private Boolean useNginx;
    @Value("${fs.nginxUrl}")
    private String nginxUrl;

    // 首页
    @RequestMapping({"/", "/index"})
    public String index() {
        return "index.html";
    }

    /**
     * 上传文件
     */
    @ResponseBody
    @PostMapping("/file/upload")
    public Map upload(@RequestParam MultipartFile file) {
        if (fileDir == null) {
            fileDir = "/";
        }
        if (!fileDir.endsWith("/")) {
            fileDir += "/";
        }
        // 文件原始名称
        String originalFileName = file.getOriginalFilename();
        String suffix = originalFileName.substring(originalFileName.lastIndexOf(".") + 1);
        String prefix = originalFileName.substring(0, originalFileName.lastIndexOf("."));
        // 保存到磁盘
        File outFile;
        String path;
        if (uuidName != null && uuidName) {
            path = getDate() + UUID.randomUUID().toString().replaceAll("-", "") + "." + suffix;
            outFile = new File(File.listRoots()[0], fileDir + path);
        } else {
            int index = 1;
            path = getDate() + originalFileName;
            outFile = new File(File.listRoots()[0], fileDir + path);
            while (outFile.exists()) {
                path = getDate() + prefix + "(" + index + ")." + suffix;
                outFile = new File(File.listRoots()[0], fileDir + path);
                index++;
            }
        }
        try {
            if (!outFile.getParentFile().exists()) {
                outFile.getParentFile().mkdirs();
            }
            file.transferTo(outFile);
            Map rs = getRS(200, "上传成功", path);
            //生成缩略图
            if (useSm != null && useSm) {
                // 获取文件类型
                String contentType = null;
                try {
                    contentType = Files.probeContentType(Paths.get(outFile.getName()));
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (contentType != null && contentType.startsWith("image/")) {
                    File smImg = new File(File.listRoots()[0], fileDir + "sm/" + path);
                    if (!smImg.getParentFile().exists()) {
                        smImg.getParentFile().mkdirs();
                    }
                    Thumbnails.of(outFile).scale(1f).outputQuality(0.25f).toFile(smImg);
                    rs.put("smUrl", "sm/" + path);
                }
            }
            return rs;
        } catch (Exception e) {
            e.printStackTrace();
            return getRS(500, e.getMessage());
        }
    }

    /**
     * 查看原文件
     */
    @GetMapping("/file/{y}/{m}/{d}/{file:.+}")
    public String file(@PathVariable("y") String y, @PathVariable("m") String m, @PathVariable("d") String d, @PathVariable("file") String filename, HttpServletResponse response) {
        String filePath = y + "/" + m + "/" + d + "/" + filename;
        if (useNginx) {
            if (nginxUrl == null) {
                nginxUrl = "/";
            }
            if (!nginxUrl.endsWith("/")) {
                nginxUrl += "/";
            }
            String newName;
            try {
                newName = URLEncoder.encode(filePath, "utf-8");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
                newName = filePath;
            }
            return "redirect:" + nginxUrl + newName;
        }
        if (fileDir == null) {
            fileDir = "/";
        }
        if (!fileDir.endsWith("/")) {
            fileDir += "/";
        }
        outputFile(fileDir + filePath, response);
        return null;
    }

    /**
     * 查看缩略图
     */
    @GetMapping("/file/sm/{y}/{m}/{d}/{file:.+}")
    public String fileSm(@PathVariable("y") String y, @PathVariable("m") String m, @PathVariable("d") String d, @PathVariable("file") String filename, HttpServletResponse response) {
        String filePath = "sm/" + y + "/" + m + "/" + d + "/" + filename;
        if (useNginx) {
            if (nginxUrl == null) {
                nginxUrl = "/";
            }
            if (!nginxUrl.endsWith("/")) {
                nginxUrl += "/";
            }
            String newName;
            try {
                newName = URLEncoder.encode(filePath, "utf-8");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
                newName = filePath;
            }
            return "redirect:" + nginxUrl + newName;
        }
        if (fileDir == null) {
            fileDir = "/";
        }
        if (!fileDir.endsWith("/")) {
            fileDir += "/";
        }
        outputFile(fileDir + filePath, response);
        return null;
    }

    // 输出文件流
    private void outputFile(String file, HttpServletResponse response) {
        // 判断文件是否存在
        File inFile = new File(File.listRoots()[0], file);
        if (!inFile.exists()) {
            PrintWriter writer = null;
            try {
                response.setContentType("text/html;charset=UTF-8");
                writer = response.getWriter();
                writer.write("<!doctype html><title>404 Not Found</title><h1 style=\"text-align: center\">404 Not Found</h1><hr/><p style=\"text-align: center\">Easy File Server</p>");
                writer.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return;
        }
        // 获取文件类型
        Path path = Paths.get(inFile.getName());
        String contentType = null;
        try {
            contentType = Files.probeContentType(path);
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (contentType != null) {
            response.setContentType(contentType);
        } else {
            response.setContentType("application/force-download");
            String newName;
            try {
                newName = URLEncoder.encode(inFile.getName(), "utf-8");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
                newName = inFile.getName();
            }
            response.setHeader("Content-Disposition", "attachment;fileName=" + newName);
        }
        // 输出文件流
        OutputStream os = null;
        FileInputStream is = null;
        try {
            is = new FileInputStream(inFile);
            os = response.getOutputStream();
            byte[] bytes = new byte[1024];
            int len;
            while ((len = is.read(bytes)) != -1) {
                os.write(bytes, 0, len);
            }
            os.flush();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                is.close();
                os.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 获取全部文件
     */
    @ResponseBody
    @RequestMapping("/api/list")
    public Map list(String dir, String accept, String exts) {
        String[] mExts = null;
        if (exts != null && !exts.trim().isEmpty()) {
            mExts = exts.split(",");
        }
        if (fileDir == null) {
            fileDir = "/";
        }
        if (!fileDir.endsWith("/")) {
            fileDir += "/";
        }
        Map<String, Object> rs = new HashMap<>();
        if (dir == null || "/".equals(dir)) {
            dir = "";
        } else if (dir.startsWith("/")) {
            dir = dir.substring(1);
        }
        File file = new File(File.listRoots()[0], fileDir + dir);
        File[] listFiles = file.listFiles();
        List<Map> dataList = new ArrayList<>();
        if (listFiles != null) {
            for (File f : listFiles) {
                if ("sm".equals(f.getName())) {
                    continue;
                }
                Map<String, Object> m = new HashMap<>();
                m.put("name", f.getName());  // 文件名称
                m.put("updateTime", f.lastModified());  // 修改时间
                m.put("isDir", f.isDirectory());  // 是否是目录
                if (f.isDirectory()) {
                    m.put("type", "dir");  // 文件类型
                } else {
                    String type;
                    m.put("url", (dir.isEmpty() ? dir : (dir + "/")) + f.getName());  // 文件地址
                    // 获取文件类型
                    Path path = Paths.get(f.getName());
                    String contentType = null;
                    String suffix = f.getName().substring(f.getName().lastIndexOf(".") + 1);
                    try {
                        contentType = Files.probeContentType(path);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    // 筛选文件类型
                    if (accept != null && !accept.trim().isEmpty() && !accept.equals("file")) {
                        if (contentType == null || !contentType.startsWith(accept + "/")) {
                            continue;
                        }
                        if (mExts != null) {
                            for (String ext : mExts) {
                                if (!f.getName().endsWith("." + ext)) {
                                    continue;
                                }
                            }
                        }
                    }
                    // 获取文件图标
                    if ("ppt".equalsIgnoreCase(suffix) || "pptx".equalsIgnoreCase(suffix)) {
                        type = "ppt";
                    } else if ("doc".equalsIgnoreCase(suffix) || "docx".equalsIgnoreCase(suffix)) {
                        type = "doc";
                    } else if ("xls".equalsIgnoreCase(suffix) || "xlsx".equalsIgnoreCase(suffix)) {
                        type = "xls";
                    } else if ("pdf".equalsIgnoreCase(suffix)) {
                        type = "pdf";
                    } else if ("html".equalsIgnoreCase(suffix) || "htm".equalsIgnoreCase(suffix)) {
                        type = "htm";
                    } else if ("txt".equalsIgnoreCase(suffix)) {
                        type = "txt";
                    } else if ("swf".equalsIgnoreCase(suffix)) {
                        type = "flash";
                    } else if ("zip".equalsIgnoreCase(suffix) || "rar".equalsIgnoreCase(suffix) || "7z".equalsIgnoreCase(suffix)) {
                        type = "zip";
                    } else if ("zip".equalsIgnoreCase(suffix) || "rar".equalsIgnoreCase(suffix) || "7z".equalsIgnoreCase(suffix)) {
                        type = "zip";
                    } else if (contentType != null && contentType.startsWith("audio/")) {
                        type = "mp3";
                    } else if (contentType != null && contentType.startsWith("video/")) {
                        type = "mp4";
                    }/* else if (contentType != null && contentType.startsWith("image/")) {
                        type = "file";
                        m.put("hasSm", true);
                        m.put("smUrl", m.get("url"));  // 缩略图地址
                    }*/ else {
                        type = "file";
                    }
                    m.put("type", type);
                    // 是否有缩略图
                    String smUrl = "sm/" + (dir.isEmpty() ? dir : (dir + "/")) + f.getName();
                    if (new File(File.listRoots()[0], fileDir + smUrl).exists()) {
                        m.put("hasSm", true);
                        m.put("smUrl", smUrl);  // 缩略图地址
                    }
                }
                dataList.add(m);
            }
        }
        // 根据上传时间排序
        Collections.sort(dataList, new Comparator<Map>() {
            @Override
            public int compare(Map o1, Map o2) {
                Long l1 = (long) o1.get("updateTime");
                Long l2 = (long) o2.get("updateTime");
                return l1.compareTo(l2);
            }
        });
        // 把文件夹排在前面
        Collections.sort(dataList, new Comparator<Map>() {
            @Override
            public int compare(Map o1, Map o2) {
                Boolean l1 = (boolean) o1.get("isDir");
                Boolean l2 = (boolean) o2.get("isDir");
                return l2.compareTo(l1);
            }
        });
        rs.put("code", 200);
        rs.put("msg", "查询成功");
        rs.put("data", dataList);
        return rs;
    }

    // 获取当前日期
    private String getDate() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy/MM/dd/");
        return sdf.format(new Date());
    }

    // 封装返回结果
    private Map getRS(int code, String msg, String url) {
        Map<String, Object> map = new HashMap<>();
        map.put("code", code);
        map.put("msg", msg);
        if (url != null) {
            map.put("url", url);
        }
        return map;
    }

    // 封装返回结果
    private Map getRS(int code, String msg) {
        return getRS(code, msg, null);
    }

    // 喵喵说要藏个🚩在这里
    private String getFlag() {
        String flag1_1 = "dGpjdGZ7anY0dl9JNV9zMF9kM";
        String flag1_2 = "WY3MWN1MTdfZjByX0M0dHN9";
        return flag1_1 + flag1_2;
    }
}
