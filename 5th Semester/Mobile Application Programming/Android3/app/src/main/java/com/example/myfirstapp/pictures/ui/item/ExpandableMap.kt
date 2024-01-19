package com.example.myfirstapp.pictures.ui.item

import androidx.compose.material3.*

import androidx.compose.animation.animateContentSize
import androidx.compose.foundation.layout.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Info
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.example.myfirstapp.pictures.utils.MyMap

@Composable
fun ExpandableMap(lat: Double, lon: Double, onLocationChanged: (Double, Double) -> Unit) {
    var isExpanded by remember { mutableStateOf(false) }
    Surface(
        modifier = Modifier
            .fillMaxWidth(),
        onClick = { isExpanded = !isExpanded }
    ) {
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp)
                .animateContentSize()
        ) {
            Row {
                Icon(
                    imageVector = Icons.Default.Info,
                    contentDescription = null
                )
                Spacer(modifier = Modifier.width(16.dp))
                Text(
                    text = "View location",
                )
            }
            if (isExpanded) {
                Spacer(modifier = Modifier.height(8.dp))
                MyMap(lat = lat, lon = lon, onLocationChanged = onLocationChanged)
            }
        }
    }
}

