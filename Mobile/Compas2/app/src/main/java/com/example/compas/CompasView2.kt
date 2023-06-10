package com.example.compas

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.animation.Animation
import android.view.animation.RotateAnimation
import android.widget.ImageView

// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 * Use the [CompasView2.newInstance] factory method to
 * create an instance of this fragment.
 */
class CompasView2 : Fragment(), CompasInterface {
    private var view: View? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        view = inflater.inflate(R.layout.fragment_compas_view2, container, false)
        return view
    }

    override fun rotateCompas(degree: Int, rotation: Int) {
        if(view!=null)
        {
            val imageView: ImageView=requireView().findViewById(R.id.imageView4)
            val rotationAnim = RotateAnimation(degree.toFloat(),rotation.toFloat(),
                Animation.RELATIVE_TO_SELF,0.5F,Animation.RELATIVE_TO_SELF,0.5F)
            rotationAnim.duration=210
            rotationAnim.fillAfter=true
            imageView.startAnimation(rotationAnim)
        }
    }
}