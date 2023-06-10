package com.example.sqltable

import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TableLayout
import android.widget.TableRow
import android.widget.TextView
import java.util.Currency
import kotlin.random.Random

class MainActivity : AppCompatActivity() {

    var arrayNames: Array<String> = arrayOf(
        "Nikolaev A.D.",
        "Shiyan I.I.",
        "Ozhgibesov V.A.",
        "Bezborodov S.M."
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var dbHelper= SQL_DatabaseHelper(this)
        for(i in 0 until arrayNames.size) dbHelper.insertData(i+1,arrayNames[i])
        var db: SQLiteDatabase=dbHelper.writableDatabase
        var cursor: Cursor =db.rawQuery("SELECT * FROM studentsTable ORDER BY Name", arrayOf())

        var tableLayout: TableLayout=findViewById(R.id.tableView)
        tableLayout.setShrinkAllColumns(true)
        tableLayout.setStretchAllColumns(true)
        var tableRow: TableRow
        var textViewArray:Array<TextView>
        var tableNames: Array<String>

        tableNames=cursor.columnNames
        tableRow= TableRow(this)
        textViewArray=Array<TextView>(cursor.columnCount,{ TextView(this) })
        for (i in 0 until textViewArray.size)
        {
            textViewArray[i].setText(tableNames[i])
            textViewArray[i].setTextSize(18F)
            textViewArray[i].setTextColor(Color.RED)
            tableRow.addView(textViewArray[i])
        }
        tableLayout.addView(tableRow)

        if(cursor.moveToFirst())
        {
            do {
                tableRow= TableRow(this)
                textViewArray=Array<TextView>(cursor.columnCount,{ TextView(this) })
                for (i in 0 until textViewArray.size)
                {
                    textViewArray[i].setText(cursor.getString(i))
                    tableRow.addView(textViewArray[i])
                }
                tableLayout.addView(tableRow)
            }while (cursor.moveToNext())
        }
    }
}