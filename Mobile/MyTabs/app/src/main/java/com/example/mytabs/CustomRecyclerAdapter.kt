package com.example.mytabs

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class CustomRecyclerAdapter(private val students: Map<String, Int>):
    RecyclerView.Adapter<CustomRecyclerAdapter.MyViewHolder>() {

    class MyViewHolder(itemView: View): RecyclerView.ViewHolder(itemView)
    {
        val picture: ImageView=itemView.findViewById<ImageView>(R.id.pictureView)
        val name: TextView=itemView.findViewById(R.id.nameView)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MyViewHolder {
        val itemView=LayoutInflater.from(parent.context).inflate(R.layout.recyclerview_item,parent,false)
        return MyViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        val key=students.keys.toTypedArray()[position]
        holder.name.text=key
        holder.picture.setImageResource(students[key]!!)
    }

    override fun getItemCount(): Int {
        return students.size
    }
}