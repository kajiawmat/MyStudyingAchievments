package com.example.livingwallpaper

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.graphics.*
import android.os.BatteryManager
import android.os.Handler
import android.service.wallpaper.WallpaperService
import android.util.Log
import android.view.SurfaceHolder

class WallpaperActivity : WallpaperService(){
    override fun onCreate()
    {
        super.onCreate()
    }

    override fun onDestroy() {
        super.onDestroy()
    }

    override fun onCreateEngine(): Engine {
        return  MyWallpaperEngine()
    }

    @Suppress("DEPRECATION")
    inner class MyWallpaperEngine: Engine()
    {

        private val handler= Handler()
        private val drawRunner = object: Runnable {
            override fun run()
            {
                draw()
            }
        }
        private var visible = true

        private var bitmap: Bitmap= BitmapFactory.decodeResource(getResources(),R.drawable.desert)
        private var wave: WavePath= WavePath(100F,100F)
        private var bitmapFish: Array<Bitmap> = arrayOf(
            BitmapFactory.decodeResource(getResources(),R.drawable.fish_right),
            BitmapFactory.decodeResource(getResources(),R.drawable.fish_left)
        )
        private var fishes: Array<Fish> = arrayOf()
        private var matrix: Matrix= Matrix()
        private var paint: Paint= Paint()
        private var level: Int=-10

        private var batterylevelReceiver= object : BroadcastReceiver() {
            override fun onReceive(context: Context?, intent: Intent?) {
                level=intent!!.getIntExtra(BatteryManager.EXTRA_LEVEL,0)
                wave.setPercent(level)
                for(i in 0 until fishes.size) fishes[i].setPercent(level)
                Log.v("Al",level.toString())
            }
        }

        init {

        }

        override fun onCreate(surfaceHolder: SurfaceHolder?) {
            super.onCreate(surfaceHolder)
            registerReceiver(batterylevelReceiver, IntentFilter(Intent.ACTION_BATTERY_CHANGED))
        }

        override fun onVisibilityChanged(visible: Boolean) {
            this.visible=visible
            if (visible)
            {
                var canvas=surfaceHolder.lockCanvas()
                var w: Float=canvas.width.toFloat()
                var h: Float=canvas.height.toFloat()
                wave= WavePath(w,h)
                wave.setPercent(level)
                fishes= arrayOf(
                    Fish(w,h,20F,25F,bitmapFish),
                    Fish(w,h,25F,45F,bitmapFish),
                    Fish(w,h,45F,65F,bitmapFish),
                    Fish(w,h,65F,85F,bitmapFish)
                )
                for (i in 0 until fishes.size) fishes[i].setPercent(level)
                matrix.reset()
                matrix.setScale((w/bitmap.width),(h/bitmap.height))
                matrix.preTranslate(0F,0F)
                surfaceHolder.unlockCanvasAndPost(canvas)
                handler.post(drawRunner)
            }
            else handler.removeCallbacks(drawRunner)
        }

        override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
            super.onSurfaceDestroyed(holder)
            this.visible=false
            handler.removeCallbacks(drawRunner)
        }

        override fun onOffsetsChanged(
            xOffset: Float,
            yOffset: Float,
            xOffsetStep: Float,
            yOffsetStep: Float,
            xPixelOffset: Int,
            yPixelOffset: Int
        ) {
            super.onOffsetsChanged(
                xOffset,
                yOffset,
                xOffsetStep,
                yOffsetStep,
                xPixelOffset,
                yPixelOffset
            )
            handler.post(drawRunner)
        }

        fun draw(){
            val holder=surfaceHolder
            var canvas: Canvas?=null
            try {
                canvas=holder.lockCanvas()
                if(canvas!=null)
                {
                    canvas.drawBitmap(bitmap,matrix,paint)
                    wave.drawWave(canvas)
                    for (i in 0 until fishes.size) fishes[i].drawFish(canvas)
                }
            }
            finally {
                if(canvas!=null) holder.unlockCanvasAndPost(canvas)
            }

            handler.removeCallbacks(drawRunner)
            if (visible) handler.postDelayed(drawRunner,30)
        }
    }
}