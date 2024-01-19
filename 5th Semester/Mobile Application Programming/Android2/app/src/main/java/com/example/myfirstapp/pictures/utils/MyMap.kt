package com.example.myfirstapp.pictures.utils

import android.util.Log
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import com.google.android.gms.maps.model.CameraPosition
import com.google.android.gms.maps.model.LatLng
import com.google.maps.android.compose.*

val TAG = "MyMap"

@Composable
fun MyMap(lat: Double, lon: Double, onLocationChanged: (Double, Double) -> Unit) {
    Log.d("MyMap!!!!", "Location: ${lat}, ${lon}")
    val markerState = rememberMarkerState(position = LatLng(lat, lon))
    val cameraPositionState = rememberCameraPositionState {
        position = CameraPosition.fromLatLngZoom(markerState.position, 10f)
    }
    GoogleMap(
        modifier = Modifier.fillMaxSize(),
        cameraPositionState = cameraPositionState,
        onMapClick = {
            Log.d(TAG, "onMapClick $it")
        },
        onMapLongClick = {
            Log.d(TAG, "onMapLongClick $it")
            markerState.position = it
            onLocationChanged(markerState.position.latitude, markerState.position.longitude)
        },
    ) {
        Marker(
            state = MarkerState(position = markerState.position),
            title = "User location title",
            snippet = "User location",
        )
    }
}
