package com.example.fragment

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView

class MainActivity : AppCompatActivity(), FragmentTwo.onDataPassListener {

    private val text_test: TextView by lazy{
        findViewById<TextView>(R.id.text_test)
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // fragment2 에 bundle 로 데이터 전달
        val fragmentTwo : FragmentTwo = FragmentTwo()
        val bundle : Bundle = Bundle()
        bundle.putString("hello","hello")
        fragmentTwo.arguments = bundle
    }

    fun receive_Menu_Button(button_Type : Int){
        text_test.text = "Hello World ${button_Type}"
    }

    override fun onDataPass(data: String?) {
        Log.d("pass", ""+data)
    }
}

