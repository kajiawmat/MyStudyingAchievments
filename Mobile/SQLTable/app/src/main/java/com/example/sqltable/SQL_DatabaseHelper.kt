package com.example.sqltable

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import kotlin.random.Random

class SQL_DatabaseHelper(context: Context): SQLiteOpenHelper(context,"FirstDataBase",null,1) {
    override fun onCreate(db: SQLiteDatabase)
    {
        db.execSQL("CREATE TABLE studentsTable("+
                "Id integer primary key autoincrement,"+
                "Name text,"+
                "Weight integer,"+
                "Height integer,"+
                "Age integer"+");")
    }
    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int)
    {
        db.execSQL("DROP TABLE IF EXISTS studentsTable")
        db.execSQL("CREATE TABLE studentsTable("+
                "Id integer primary key autoincrement,"+
                "Name text,"+
                "Weight integer,"+
                "Height integer,"+
                "Age integer"+");")
    }
    fun insertData(id: Int,name: String)
    {
        var db=writableDatabase
        var contentValues=ContentValues()
        contentValues.put("Id",id)
        contentValues.put("Name",name)
        contentValues.put("Weight", Random.nextInt(30)+70)
        contentValues.put("Height", Random.nextInt(30)+160)
        contentValues.put("Age", Random.nextInt(3)+19)
        db.insert("studentsTable",null,contentValues)
    }
}