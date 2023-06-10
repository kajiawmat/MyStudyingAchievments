package com.example.mytabs

import android.media.Image
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView



/**
 * A simple [Fragment] subclass.
 * Use the [FragmentList.newInstance] factory method to
 * create an instance of this fragment.
 */
private val students: Map<String,Int> = mapOf(
    "Баранец И.А." to R.drawable.yes,
    "Авазов Д.Р." to R.drawable.no,
    "Безбородов С.М." to R.drawable.yes,
    "Бычик С.М." to R.drawable.no,
    "Волокитин Е.Н." to R.drawable.yes,
    "Воропаев Е.Н." to R.drawable.yes,
    "Герасимов Б.Д." to R.drawable.no,
    "Глухов Н.А." to R.drawable.no,
    "Губкина А.А." to R.drawable.no,
    "Даваа М.А." to R.drawable.no,
    "Дегтярёв И.С." to R.drawable.no,
    "Дубинина В.В." to R.drawable.yes,
    "Зыбин А.М." to R.drawable.no,
    "Калуга А.Е." to R.drawable.no,
    "Кондратьев Ю.Е." to R.drawable.yes,
    "Котул Д.А." to R.drawable.no,
    "Кочин Д.А." to R.drawable.no,
    "Краскова А.Н." to R.drawable.no,
    "Ледовский Д.Е." to R.drawable.no,
    "Маланов Р.И." to R.drawable.no,
    "Малашенко В.С." to R.drawable.no,
    "Николаев А.Д." to R.drawable.yes,
    "Ожгибесов В.А." to R.drawable.yes,
    "Перминов И.С." to R.drawable.no,
    "Полушкин К.А." to R.drawable.yes,
    "Санданов Т.А." to R.drawable.no,
    "Серебряков В.Р." to R.drawable.no,
    "Ситников В.М." to R.drawable.yes,
    "Фёдоров Д.П." to R.drawable.no,
    "Фоменко Е.В." to R.drawable.yes,
    "Харченко Е.В." to R.drawable.yes,
    "Хен Б.Д." to R.drawable.no,
    "Шиян И.И." to R.drawable.yes
)

class FragmentList() : Fragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //recyclerView.layoutManager=LinearLayoutManager(view)
        //recyclerView.adapter=CustomRecyclerAdapter(students)

    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view: View = inflater.inflate(R.layout.fragment_list,container,false)
        val recyclerView: RecyclerView = view.findViewById(R.id.recyclerView)
        recyclerView.adapter=CustomRecyclerAdapter(students)
        recyclerView.layoutManager=LinearLayoutManager(view.context)
        return view
    }


}