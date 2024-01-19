package com.example.myfirstapp.pictures.ui.items

import android.app.Application
import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.myfirstapp.pictures.data.Picture
import com.example.myfirstapp.sensors.ProximitySensorViewModel

typealias OnItemFn = (id: String?) -> Unit

@Composable
fun ItemList(pictureList: List<Picture>, onItemClick: OnItemFn, modifier: Modifier) {
    val proximitySensorViewModel = viewModel<ProximitySensorViewModel>(
        factory = ProximitySensorViewModel.Factory(
            LocalContext.current.applicationContext as Application
        )
    )
    Log.d("ItemList", "recompose")
    val sortedPictures = pictureList.sortedBy { it.dateOfRelease }
    LazyColumn(
        modifier = modifier
            .fillMaxSize()
            .padding(12.dp)
    ) {
        items(sortedPictures) { item ->
            Spacer(modifier = Modifier.height(3.dp))
            ItemDetail(item, onItemClick, fontSize = proximitySensorViewModel.uiState + 10)
            Spacer(modifier = Modifier.height(3.dp))
        }
    }
}

@Composable
fun ItemDetail(picture: Picture, onItemClick: OnItemFn, fontSize: Float = 24.0f) {
    Log.d("ItemDetail", "recompose id = ${picture._id}, title: ${picture.title}")
    Row(
        modifier = Modifier
            .fillMaxWidth() // This will make the Row take the full width of its parent
            .background(
                color = if (picture.isSaved) Color(0xFF2255AA) else Color(0xFFAA2222),
                shape = RoundedCornerShape(30.dp)
            )

            .border(
                width = 3.dp,
                color = if (picture.isSaved) Color(0xFF1188FF) else Color(0xFFFF0000),
                shape = RoundedCornerShape(30.dp)
            )
            .padding(
                start = 6.dp,
                top = 8.dp,
                end = 6.dp,
                bottom = 8.dp)
            .clickable { onItemClick(picture._id) }
    ) {
        Column(
            modifier = Modifier
                .padding(16.dp)
        ) {
            Text(
                text = picture.title,
                style = TextStyle(
                    fontSize = (fontSize + 8).sp,
                    fontWeight = FontWeight.Bold,
                    color = Color.White
                )
            )
            Text(
                text = picture.description,
                style = TextStyle(
                    color = Color.White,
                    fontSize = (fontSize + 2).sp,
                    fontStyle = FontStyle.Italic
                )
            )
            Text(
                text = "- URL: ${picture.imageUrl}",
                style = TextStyle(
                    fontSize = fontSize.sp,
                )
            )
            Text(
                text = "- DateOfRelease: ${picture.dateOfRelease}",
                style = TextStyle(
                    fontSize = fontSize.sp,
                )
            )
            Text(
                text = "- Is ${if (picture.isPhotography) "" else "not "}Photography",
                style = TextStyle(
                    fontSize = fontSize.sp,
                )
            )
            Text(
                text = "- Is ${if (picture.isSaved) "" else "not "}Saved",
                style = TextStyle(
                    fontSize = fontSize.sp,
                )
            )
        }
    }
}
