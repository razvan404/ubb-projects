package com.artgallery.ui.pictureList

import android.content.ContentValues.TAG
import android.util.Log
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.rounded.Add
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.artgallery.R

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun PictureListScreen(onRowClick: (id: String?) -> Unit, onAddPicture: () -> Unit, onLogout: () -> Unit) {
    Log.d(TAG, "recompose")
    val pictureListViewModel = viewModel<PictureListViewModel>(factory = PictureListViewModel.Factory)
    val picturesUiState by pictureListViewModel.uiState.collectAsStateWithLifecycle(
        initialValue = listOf()
    )
    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text(text = stringResource(id = R.string.picturesListTitle)) },
                actions = {
                    Button(onClick = onLogout) { Text("Logout") }
                }
            )
        },
        floatingActionButton = {
            FloatingActionButton(
                onClick = {
                    Log.d(TAG, "add")
                    onAddPicture()
                },
            ) { Icon(Icons.Rounded.Add, "Add") }
        }
    ) {
        PictureList(
            picturesList = picturesUiState,
            onRowClick = onRowClick,
            modifier = Modifier.padding(it)
        )
    }
}

@Preview
@Composable
fun PreviewItemsScreen() {
    PictureListScreen(onRowClick = {}, onAddPicture = {}, onLogout = {})
}
