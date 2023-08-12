package com.example.diary

import android.content.Context
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.edit
import androidx.core.widget.addTextChangedListener

class DiaryActivity : AppCompatActivity() {
    private val diaryEditText : EditText by lazy { findViewById<EditText>(R.id.diaryEditText) }
    private val handler = Handler(Looper.getMainLooper()) //메인스레드에 연결된 핸들러 생성
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_diary)

        val detailPreferences = getSharedPreferences("diary", Context.MODE_PRIVATE)

        diaryEditText.setText(detailPreferences.getString("detail", ""))

        //특정 상태에 저장되게 구현
        val runnable = Runnable {
            getSharedPreferences("diary", Context.MODE_PRIVATE).edit{
                putString("detail", diaryEditText.text.toString())
            }
            Log.d("DiaryActivity", "Save!!")
        }

        diaryEditText.addTextChangedListener {

            //이렇게만 사용하면 한글자씩 계속 저장됨
            //detailPreferences.edit{
            //putString("detail", diaryEditText.text.toString())
            //}
            Log.d("DiaryActivity", "TextChanged :: $it")
            //0.5이전에 아직 실행되지 않고 펜딩되어있는 runnable이 있다면 지우기 위한 작업
            handler.removeCallbacks(runnable)
            //0.5초이후 스레드 실행
            handler.postDelayed(runnable, 500)
        }

    }
}