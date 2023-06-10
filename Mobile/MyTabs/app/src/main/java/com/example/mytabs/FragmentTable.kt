package com.example.mytabs

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TableLayout
import android.widget.TableRow
import android.widget.TextView
import com.example.mytabs.ui.main.SchoolItem

// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

val schoolItems: Array<SchoolItem> = arrayOf(
    SchoolItem("Ручка шариковая",30, 20,500),
    SchoolItem("Ручка гелевая",20, 40,700),
    SchoolItem("Простой карандаш",40, 15,600),
    SchoolItem("Цв. карандаши (6)",15, 100,1300),
    SchoolItem("Цв. карандаши (12)",20, 220,4000),
    SchoolItem("Тетрадь (12 л.)",30, 25,700),
    SchoolItem("Тетрадь (24 л.)",30, 60,1500),
    SchoolItem("Тетрадь (48 л.)",30, 120,3000)
)

class FragmentTable : Fragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

    }

    @SuppressLint("ResourceAsColor")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view: View = inflater.inflate(R.layout.fragment_table, container, false)
        val table: TableLayout = view.findViewById(R.id.tableView)
        table.setShrinkAllColumns(true)
        table.setStretchAllColumns(true)
        var row: TableRow= TableRow(view.context)
        var txts: Array<TextView> =arrayOf(
            TextView(view.context),
            TextView(view.context),
            TextView(view.context),
            TextView(view.context)
        )
        for(i in 0..3) txts[i].setTextSize(18.0F)
        txts[0].setText("Школьная вещь")
        row.addView(txts[0])
        txts[1].setText("Кол-во")
        row.addView(txts[1])
        txts[2].setText("Цена,шт")
        row.addView(txts[2])
        txts[3].setText("Опт. цена")
        row.addView(txts[3])
        table.addView(row)
        for(i in 0 until schoolItems.size)
        {
            row=fillRow(i,view)
            table.addView(row)
        }
        return view
    }

    fun fillRow(index: Int, view: View): TableRow
    {
        val row: TableRow= TableRow(this.context)
        var txts: Array<TextView> =arrayOf(
            TextView(view.context),
            TextView(view.context),
            TextView(view.context),
            TextView(view.context)
        )
        txts[0].setText(schoolItems[index].name)
        row.addView(txts[0])
        txts[1].setText(schoolItems[index].number.toString())
        row.addView(txts[1])
        txts[2].setText(schoolItems[index].price.toString())
        row.addView(txts[2])
        txts[3].setText(schoolItems[index].optPrice.toString())
        row.addView(txts[3])
        return row
    }
}