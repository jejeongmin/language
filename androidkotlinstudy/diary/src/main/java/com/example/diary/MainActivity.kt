package com.example.diary

import android.content.Context
import android.content.Intent
import android.content.SharedPreferences
import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.NumberPicker
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.widget.AppCompatButton
import androidx.core.content.edit

class MainActivity : AppCompatActivity() {
    private val numberPicker1 : NumberPicker by lazy {
        findViewById<NumberPicker>(R.id.numberPicker1)
            .apply{
                minValue = 0
                maxValue = 9
            }
    }
    private val numberPicker2 : NumberPicker by lazy {
        findViewById<NumberPicker>(R.id.numberPicker2)
            .apply{
                minValue = 0
                maxValue = 9
            }
    }
    private val numberPicker3 : NumberPicker by lazy {
        findViewById<NumberPicker>(R.id.numberPicker3)
            .apply{
                minValue = 0
                maxValue = 9
            }
    }

    private val openButton : AppCompatButton by lazy{
        findViewById<AppCompatButton>(R.id.openButton)
    }
    private val changePasswordButton : AppCompatButton by lazy{
        findViewById<AppCompatButton>(R.id.changePasswordButton)
    }
    private var changePasswordMode = false
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        //view는 onCreate이후 그려지기 때문에 호출해주지 않으면 min, max 설정한 값이 할당되지 않음
        numberPicker1
        numberPicker2
        numberPicker3

        openButton.setOnClickListener {
            if(changePasswordMode){
                Toast.makeText(this,"비밀번호 변경중인 상태", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val passwordPreferences:SharedPreferences = getSharedPreferences("password", Context.MODE_PRIVATE) //나만 사용할 수 있도록 MODE_PRIVATE
            val passwordFromUser : String = "${numberPicker1.value}${numberPicker2.value}${numberPicker3.value}"
            if(passwordPreferences.getString("password", "000").equals(passwordFromUser)){ //초기 패스워드
                //TODO 다이어리 페이지 작성 후 넘겨줌
                startActivity(Intent(this, DiaryActivity::class.java))
            }else{
                showErrorAlertDialog()
            }
        }

        changePasswordButton.setOnClickListener {
            val passwordPreferences:SharedPreferences = getSharedPreferences("password", Context.MODE_PRIVATE)
            val passwordFromUser : String = "${numberPicker1.value}${numberPicker2.value}${numberPicker3.value}"
            if(changePasswordMode){ // true면 저장
                passwordPreferences.edit{
                    putString("password", passwordFromUser)
                    //저장에는 2개 방법이 있음 -> commit - > 다 저장까지 ui 정지, apply -> 비동기적으로 저장
                }

                changePasswordMode = false
                changePasswordButton.setBackgroundColor(Color.BLACK)

            }else{ //false면 changepasswordMode 활성화 -> 비밀번호 맞는지 체크
                if(passwordPreferences.getString("password", "000").equals(passwordFromUser)){ //초기 패스워드
                    changePasswordMode = true
                    Toast.makeText(this, "변경할 패스워드 입력", Toast.LENGTH_SHORT).show()
                    changePasswordButton.setBackgroundColor(Color.RED)
                }else{
                    showErrorAlertDialog()
                }
            }
        }
    }
    private fun showErrorAlertDialog(){
        AlertDialog.Builder(this)
            .setTitle("실패")
            .setMessage("비밀번호가 다릅니다.")
            .setPositiveButton("확인") { _ , _ -> } //dialog, which 변수를 사용하지 않기 때문에 언더바로 처리
            .create()
            .show()
    }

}