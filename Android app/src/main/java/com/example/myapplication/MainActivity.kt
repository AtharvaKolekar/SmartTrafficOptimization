package com.example.myapplication

import   androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.Manifest
import android.content.pm.PackageManager
import android.os.Looper
import android.util.Log
import android.widget.Switch
import android.widget.TextView
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.google.android.gms.location.*
import android.annotation.SuppressLint
import android.webkit.WebView
import android.webkit.WebViewClient
import com.google.firebase.database.FirebaseDatabase


class MainActivity : AppCompatActivity() {

    private lateinit var fusedLocationClient: FusedLocationProviderClient
    private lateinit var locationRequest: LocationRequest

    companion object {
        private const val PERMISSIONS_REQUEST_LOCATION = 1001
    }

    var switch=1

    private lateinit var webView: WebView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        webView = findViewById(R.id.webView)
        webView.settings.javaScriptEnabled = true
        webView.webViewClient = WebViewClient()
        WebView.setWebContentsDebuggingEnabled(true)

        // Load the Leaflet map HTML file from the assets folder
        webView.loadUrl("file:///android_asset/leaflet_map.html")

        fusedLocationClient = LocationServices.getFusedLocationProviderClient(this)
        locationRequest = LocationRequest.create()
            .setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY)
            .setInterval(2000)  // Update location every 10 seconds
            .setFastestInterval(1000) // The fastest update interval, in milliseconds

        findViewById<Switch>(R.id.switch1).setOnCheckedChangeListener { buttonView, isChecked ->
            // Implement your logic here based on the switch state (isChecked)
            if (isChecked) {
                // If switch is checked (ON), perform action
                // For example, start emergency mode
                switch=1
            } else {
             switch=0
            }
        }


        // Check and request permissions
        if (ContextCompat.checkSelfPermission(
                this,
                Manifest.permission.ACCESS_FINE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.ACCESS_FINE_LOCATION),
                PERMISSIONS_REQUEST_LOCATION
            )
        } else {
            // Request location updates
            fusedLocationClient.requestLocationUpdates(
                locationRequest,
                locationCallback,
                Looper.getMainLooper()
            )
        }


    }

    private val locationCallback = object : LocationCallback() {
        override fun onLocationResult(locationResult: LocationResult) {
            super.onLocationResult(locationResult)
            val location = locationResult.lastLocation
            // Handle location updates here
            location?.let {
                // Print location data
val ref=FirebaseDatabase.getInstance().reference.child("users").child("user1")

                if(switch==1){
                    val uniqueKey =ref.push().key
                    ref.child("lattitude").setValue(it.latitude.toString())
                    ref.child("longitude").setValue(it.longitude.toString())
//                    ref.child("Junc")
                    findViewById<TextView>(R.id.editTextLongitude).text=it.longitude.toString()

                    findViewById<TextView>(R.id.editTextLatitude).text=it.latitude.toString()

                }


                Log.d(
                    "LocationData",
                    "Latitude: ${it.latitude}, Longitude: ${it.longitude}, Accuracy: ${it.accuracy} meters"
                )
                // Or you can update UI with this location data
            }
        }
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == PERMISSIONS_REQUEST_LOCATION) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // Permission granted, request location updates
                if (ActivityCompat.checkSelfPermission(
                        this,
                        Manifest.permission.ACCESS_FINE_LOCATION
                    ) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(
                        this,
                        Manifest.permission.ACCESS_COARSE_LOCATION
                    ) != PackageManager.PERMISSION_GRANTED
                ) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return
                }
                fusedLocationClient.requestLocationUpdates(
                    locationRequest,
                    locationCallback,
                    Looper.getMainLooper()
                )
            } else {
                // Permission denied
                // Handle this case as per your app's requirements
            }
        }
    }
}