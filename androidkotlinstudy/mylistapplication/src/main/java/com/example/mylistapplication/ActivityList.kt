package com.example.mylistapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Toast
import com.example.mylistapplication.databinding.ActivityListBinding
import java.util.Random

class ActivityList : AppCompatActivity() {

    val TAG = "ListActivity"
    var db : AppDatabase? = null
    var contactsList = mutableListOf<Contacts>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        var binding = ActivityListBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val adapter = ContactsListAdapter(contactsList)

        adapter.setItemClickListener(object : ContactsListAdapter.OnItemClickListener {
            override fun onClick(v: View, position: Int) {
                val contacts = contactsList[position]

                db?.contactsDao()?.delete(contacts = contacts) //DB에서 삭제
                contactsList.removeAt(position) //리스트에서 삭제
                adapter.notifyDataSetChanged() //리스트뷰 갱신

                Log.d(TAG, "remove item($position). name:${contacts.name}")
            }
        })

        binding.mPlusButton.setOnClickListener {
            //랜덤 번호 만들기
            val random = Random()
            val numA = random.nextInt(1000)
            val numB = random.nextInt(10000)
            val numC = random.nextInt(10000)
            val rndNumber = String.format("%03d-%04d-%04d",numA,numB,numC)

            val contact = Contacts(0, "New $numA", rndNumber) //Contacts 생성
            db?.contactsDao()?.insertAll(contact) //DB에 추가
            contactsList.add(contact) //리스트 추가

            adapter.notifyDataSetChanged() //리스트뷰 갱신
        }

        binding.mRecyclerView.adapter = adapter
    }
}