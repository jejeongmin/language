package com.example.mylistapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.example.mylistapplication.databinding.ItemContactsBinding

class ContactsListAdapter(private val itemList : List<Contacts>) : RecyclerView.Adapter<ContactsViewHolder>()  {

    override fun getItemCount(): Int {
        return itemList.size
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ContactsViewHolder =
        ContactsViewHolder(
            ItemContactsBinding.inflate(LayoutInflater.from(parent.context), parent,
            false))

    override fun onBindViewHolder(holder: ContactsViewHolder, position: Int) {
        val item = itemList[position]

        holder.itemView.setOnClickListener {
            itemClickListener.onClick(it, position)
        }

        holder.apply {
            binding.mName.text = item.name
            binding.mTel.text = item.tel
        }
    }

    //ClickListener
    interface OnItemClickListener {
        fun onClick(v: View, position: Int)
    }
    private lateinit var itemClickListener : OnItemClickListener

    fun setItemClickListener(itemClickListener: OnItemClickListener) {
        this.itemClickListener = itemClickListener
    }

}