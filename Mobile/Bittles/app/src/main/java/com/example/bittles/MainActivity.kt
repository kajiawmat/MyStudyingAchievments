package com.example.bittles

import android.content.Context
import android.graphics.*
import android.media.MediaPlayer
import android.media.MediaPlayer.OnPreparedListener
import android.media.SoundPool
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.MotionEvent
import android.view.MotionEvent.ACTION_DOWN
import android.view.View
import android.view.Window
import android.view.WindowManager

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        requestWindowFeature(Window.FEATURE_NO_TITLE)
        this.window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN)
        supportActionBar!!.hide()
        window.decorView.apply {
            systemUiVisibility= View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or View.SYSTEM_UI_FLAG_FULLSCREEN
        }
        setContentView(Panel(this))
    }
    class Panel(context: Context) : View(context)
    {
        private var length: Int=0
        var flag:Boolean=false
        var bugs: Array<BugView> = arrayOf()
        var score: Long=0
        var lives: Int=3
        var paint= Paint()
        var mediaPlayer=MediaPlayer.create(context,R.raw.theme_nile)
        var soundPlayer=MediaPlayer.create(context,R.raw.collapse_scarab)
        init {
            mediaPlayer.isLooping=true
            soundPlayer.setVolume(0.3F,0.3F)
            this.setOnTouchListener { v, event ->
                if(event is MotionEvent && event.action==ACTION_DOWN)
                {
                    if(bugs.size!=0)
                    {
                        var _flag=false
                        var _x:Float=event.x
                        var _y:Float=event.y
                        var _x0:Float
                        var _y0:Float
                        var _w:Float
                        var _h:Float
                        for(i in 0 until bugs.size)
                        {
                            _x0=bugs[i].x
                            _y0=bugs[i].y
                            _w=bugs[i].W()
                            _h=bugs[i].H()
                            if((_x-_x0)*(_x-_x0)/(_w*_w)+(_y-_y0)*(_y-_y0)/(_h*_h)<=1F)
                            {
                                _flag=true
                                if(bugs[i].alive)
                                {
                                    bugs[i].alive=false
                                    AddScore()
                                    soundPlayer.stop()
                                    soundPlayer.prepare()
                                    soundPlayer.seekTo(300)
                                    soundPlayer.start()
                                    break
                                }
                            }
                        }
                        if(!_flag) DelLive()
                    }
                    else
                    {
                        score=0L
                        lives=3
                        flag=true
                        mediaPlayer.stop()
                    }
                }
                true
            }
        }

        override fun onDraw(canvas: Canvas?) {
            if(flag) {
                mediaPlayer.prepare()
                mediaPlayer.start()
                bugs = Array<BugView>(8,{BugView(this.context,width.toFloat(),height.toFloat())})
            }
            flag=false
            paint.setColor(Color.WHITE)
            paint.textSize=75F
            var matrix: Matrix = Matrix()
            var bitMap=BitmapFactory.decodeResource(getResources(),R.drawable.background)
            matrix.postScale((width/bitMap.width*2).toFloat(),(height/bitMap.height*2).toFloat())
            matrix.postTranslate(0F,0F)
            canvas!!.drawBitmap(bitMap,matrix,paint)
            if(bugs.size==0)
            {
                paint.setColor(Color.BLACK)
                paint.alpha=150
                canvas!!.drawRect(0F,0F,width.toFloat(),height.toFloat(),paint)
                paint.setColor(Color.WHITE)
                canvas!!.drawText("Нажмите на экран, чтобы начать...",width/2-600F,height/2+0F,paint)
            }
            for(i in 0 until bugs.size)
            {
                bugs[i].draw(canvas)
            }
            canvas.drawText("Очки:  "+score.toString(),width-600F,100F,paint)
            canvas.drawText("Жизни: "+lives.toString(),width-600F,200F,paint)
            invalidate()
        }

        private fun AddScore()
        {
            score+=100L
            if(score%5000L==0L) lives++
        }

        private fun DelLive()
        {
            lives--
            if(lives==0) {
                bugs= arrayOf()
                mediaPlayer.stop()
            }
        }

        override fun onWindowFocusChanged(hasWindowFocus: Boolean) {
            super.onWindowFocusChanged(hasWindowFocus)
            if (!hasWindowFocus)
            {
                mediaPlayer.pause()
                length=mediaPlayer.currentPosition
            }
            else
            {
                mediaPlayer.seekTo(length)
                if(bugs.size!=0) mediaPlayer.start()
            }
        }
    }
}