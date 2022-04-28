package com.example.easydroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import com.example.easydroid.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity(),View.OnClickListener {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        var button=findViewById<Button>(R.id.button);
        button.setOnClickListener(this)
        // Example of a call to a native method
//        binding.sampleText.text = stringFromJNI()
    }

    /**
     * A native method that is implemented by the 'easydroid' native library,
     * which is packaged with this application.
     */
    // 置换
    fun enc(s:String):String{
        var len=s.length;
        var sa=s.toCharArray();
        var i=0;
        while(i<len-1){
            var tmp=sa[i]
            sa[i]=sa[i+1]
            sa[i+1]=tmp
            i+=2
        }
        i=0
        while(i<len/2){
            var tmp=sa[i]
            sa[i]=sa[len-i-1]
            sa[len-i-1]=tmp
            i+=1
        }
        return String(sa)
    }
    external fun stringFromJNI(s:String): String

    companion object {
        // Used to load the 'easydroid' library on application startup.
        init {
            System.loadLibrary("easydroid")
        }
    }
    private fun check(s:String):Boolean{
        var t=enc(stringFromJNI(s))
        return t=="v6tSJPtwvQz83l4Ti7sSN6uQnBog3Yttj+3SJ73g"
    }
    override fun onClick(p0: View?) {
        var et=findViewById<EditText>(R.id.editTextTextPersonName);
        if(check(et.text.toString())){
            Toast.makeText(this,"Right",Toast.LENGTH_LONG).show()
        }else{
            Toast.makeText(this,"Wrong",Toast.LENGTH_LONG).show()
        }
    }
}