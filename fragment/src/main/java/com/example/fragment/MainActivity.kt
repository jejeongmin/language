package com.example.fragment

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    private val text_test: TextView by lazy{
        findViewById<TextView>(R.id.text_test)
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun receive_Menu_Button(button_Type : Int){
        text_test.text = "Hello World ${button_Type}"
    }
}

