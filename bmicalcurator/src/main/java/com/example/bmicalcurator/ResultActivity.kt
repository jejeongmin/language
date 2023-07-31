package com.example.bmicalcurator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import kotlin.math.pow

class ResultActivity : AppCompatActivity(){
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_result)

        val height = intent.getDoubleExtra("height", 0.0)
        val weight = intent.getDoubleExtra("weight", 0.0)
        val bmi:Double = weight / (height / 100).pow(2.0)
        val resultText:String = when{
            bmi >= 35.0 -> "고도 비만"
            bmi >= 30.0 -> "중도 비만"
            bmi >= 25.0 -> "경도 비만"
            bmi >= 23.0 -> "과체중"
            bmi >= 18.5 -> "정상"
            else -> "저체중"
        }

        val resultValueTextView: TextView = findViewById(R.id.bmiResultTextView)
        val resultStringTextView:TextView = findViewById(R.id.resultTextView)

        resultValueTextView.text = bmi.toString()
        resultStringTextView.text = resultText
    }
}