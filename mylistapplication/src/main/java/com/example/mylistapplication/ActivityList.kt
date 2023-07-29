package com.example.mylistapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Toast
import com.example.mylistapplication.databinding.ActivityListBinding

class ActivityList : AppCompatActivity() {

    var contactsList = mutableListOf(
        Contacts("john","010-0000-11111"),
        Contacts("mir","010-1111-2222"),
        Contacts("delp", "010-3333-4444"),
        Contacts("jacob", "010-3333-5555"),
        Contacts("sheu", "010-3333-6666"),
        Contacts("ma", "010-3333-7777"),
        Contacts("ham", "010-3333-8889")
    )

    var count = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        var binding = ActivityListBinding.inflate(layoutInflater)
        setContentView(binding.root)

        val adapter = ContactsListAdapter(contactsList)

        adapter.setItemClickListener(object : ContactsListAdapter.OnItemClickListener {
            override fun onClick(v: View, position: Int) {
                val item = contactsList[position]

                //Toast.makeText(v.context, "Activity\n${item.name}\n${item.tel}", Toast.LENGTH_SHORT).show()
                //item.name = item.name + "1"
                contactsList.removeAt(position)

                adapter.notifyDataSetChanged()
            }
        })

        binding.mPlusButton.setOnClickListener {
            var contact = Contacts("Add ${count++}","000-0000-00000")
            contactsList.add(contact)

            adapter.notifyDataSetChanged()
        }

        binding.mRecyclerView.adapter = adapter
    }
}