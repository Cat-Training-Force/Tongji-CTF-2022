package com.tjctf.api;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class MeowController {

    @GetMapping("/meow")
    public String greetingForm(Model model) {
        model.addAttribute("meow", new Meow());
        return "meow";
    }

    @PostMapping("/meow")
    public String meowSubmit(@ModelAttribute Meow meow, Model model) {
        return "meow";
    }

}
