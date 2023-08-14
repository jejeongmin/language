package com.example.livedata

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Observer

class MainActivity : AppCompatActivity() {

    private var count = 0;
    private var liveText : MutableLiveData<String> = MutableLiveData<String>().set("Hello World ${++count}")
    private val text_test: TextView by lazy{
        findViewById<TextView>(R.id.text_test)
    }
    private val btn_change: Button by lazy{
        findViewById<Button>(R.id.btn_Change)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        liveText.observe(this, Observer{
            text_test.text = it
        })

        btn_change.setOnClickListener {
            liveText.value = "Hello World ${++count}"
        }
    }
}

private fun MutableLiveData<String>.set(value:String) : MutableLiveData<String>{
    this.value = value
    return this
}