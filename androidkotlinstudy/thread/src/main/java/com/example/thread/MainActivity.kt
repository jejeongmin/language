package com.example.thread

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.example.thread.R
import com.example.thread.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private var cnt: Int = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        var binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val runnable: Runnable = object : Runnable {
            override fun run() {
                while (cnt < 100) {
                    Log.d("Thread-1", "${cnt++}")
                }
            }
        }
        val thread: Thread = Thread(runnable)
        binding.button1.setOnClickListener {

            thread.start()
        }

        binding.button2.setOnClickListener {
            Thread(object : Runnable {
                override fun run() {
                    var cnt2 : Int = 0
                    while (cnt2 < 100) {
                        Log.d("Thread-2", "${cnt2++}")
                    }
                }
            }).start()
        }

        binding.button3.setOnClickListener {

            Thread(Runnable {
                var cnt3 : Int = 0
                while (cnt3 < 100) {
                    Log.d("Thread-3", "${cnt3++}")
                    Thread.sleep(2000)

                    runOnUiThread {

                        if (cnt3 % 2 == 0) {
                            binding.root.setBackgroundColor(R.color.white)
                        } else {
                            binding.root.setBackgroundColor(R.color.black)
                        }
                    }
                }
            }).start()

        }
    }
}