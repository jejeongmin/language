package com.example.myapplication.activity

import android.app.Activity
import android.os.Bundle
import android.widget.Toast
import com.example.myapplication.R
import com.example.myapplication.databinding.ActivityHelloBinding

class HelloActivity : Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        var binding = ActivityHelloBinding.inflate(layoutInflater)

        setContentView(binding.root)

        binding.btnHello.setOnClickListener(){
            //클릭시 동작할 코드 작성 필요
            Toast.makeText(this, "토스트 메시지", Toast.LENGTH_SHORT).show()
        }
    }
}