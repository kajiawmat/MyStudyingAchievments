package com.example.livingwallpaper

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.os.BatteryManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var receiver = object : BroadcastReceiver() {
            override fun onReceive(context: Context?, intent: Intent?) {
                var level=intent!!.getIntExtra(BatteryManager.EXTRA_LEVEL,0)
                Log.v("Alex",level.toString())
            }
        }
        registerReceiver(receiver, IntentFilter(Intent.ACTION_BATTERY_CHANGED))

    }
}