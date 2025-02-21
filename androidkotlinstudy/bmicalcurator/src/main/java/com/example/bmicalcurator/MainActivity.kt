package com.example.bmicalcurator

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.EditText
import android.widget.Toast

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val heightEditText: EditText = findViewById(R.id.heightEditText)
        val weightEditText: EditText = findViewById(R.id.weightEditText)
        val resultButton: Button = findViewById(R.id.resultButton)

        /*
            함수 안에서 return 을 사용하면 해당 함수의 반환값으로 인식됩니다.
            특히 onClickListener와 같이 람다식을 사용할 경우는 return 이 클릭리스너에 대한 것인지 함수에 대한 것인지 구분하기가 어려운데
            이럴때 return 의 대상을 명시하기 위해서 @(at) 을 붙힙니다.
            return@(어디)클릭리스너 이런식입니다.
         */
        resultButton.setOnClickListener{
            Log.d("MainActivity", "Result버튼의 클릭되었음")
            if(heightEditText.text.isEmpty() || weightEditText.text.isEmpty()) {
                Toast.makeText(this, "빈 값이 있습니다.", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val height: Double = heightEditText.text.toString().toDouble()
            val weight: Double = weightEditText.text.toString().toDouble()

            val intent = Intent(this, ResultActivity::class.java)
            intent.putExtra("height", height)
            intent.putExtra("weight", weight)
            startActivity(intent)
        }
    }
}