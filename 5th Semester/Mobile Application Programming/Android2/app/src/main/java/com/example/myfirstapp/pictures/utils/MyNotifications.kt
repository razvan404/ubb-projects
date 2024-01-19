package com.example.myfirstapp.pictures.utils

import android.util.Log
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.myfirstapp.core.Result
import com.example.myfirstapp.pictures.ui.item.ItemViewModel

@Composable
fun MyNotifications() {
    val itemViewModel = viewModel<ItemViewModel>(factory = ItemViewModel.Factory(null))
    val itemUiState = itemViewModel.uiState

    val context = LocalContext.current
    val channelId = "MyTestChannel"
    val notificationId = 0

    Log.d("My notifications", "Recompose")
    LaunchedEffect(Unit) {
        createNotificationChannel(channelId, context)
    }

    LaunchedEffect(itemUiState.submitResult) {
        Log.d("My notifications", "Submit = ${itemUiState.submitResult}");
        if (itemUiState.submitResult is Result.Success) {
            showSimpleNotification(
                context,
                channelId,
                notificationId,
                "New simple notification",
                "Saved picture!"
            )
        }
        if(itemUiState.submitResult is Result.Error){
            showSimpleNotification(
                context,
                channelId,
                notificationId,
                "New simple notification",
                "Saved picture locally!"
            )
        }
    }
}
