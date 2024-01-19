package com.example.myfirstapp

import Permissions
import android.Manifest
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import com.example.myfirstapp.core.TAG
import androidx.compose.foundation.layout.height
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.lifecycleScope
import com.example.myfirstapp.pictures.utils.MyNetworkStatus
import com.example.myfirstapp.ui.theme.MyFirstAppTheme
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            Log.d(TAG, "onCreate")

            MyApp(
                networkStatus = { MyNetworkStatus() },
                content = { MyAppNavHost() }
            )
        }
    }

    override fun onResume() {
        super.onResume()
        lifecycleScope.launch {
            (application as MyFirstApplication).container.itemRepository.openWsClient()
        }
    }

    override fun onPause() {
        super.onPause()
        lifecycleScope.launch {
            (application as MyFirstApplication).container.itemRepository.closeWsClient()
        }
    }

}

@OptIn(ExperimentalPermissionsApi::class)
@Composable
fun MyApp(networkStatus: @Composable () -> Unit, content: @Composable () -> Unit) {
    Log.d("MyFirstApp", "recompose")
    MyFirstAppTheme {
        Surface {
            Column {
                networkStatus()
                Spacer(modifier = Modifier.height(8.dp))
                Permissions(
                    permissions = listOf(
                        Manifest.permission.ACCESS_COARSE_LOCATION,
                        Manifest.permission.ACCESS_FINE_LOCATION
                    ),
                    rationaleText = "Please allow app to use location",
                    dismissedText = "No location provider allowed!"
                )
                content()
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    MyFirstAppTheme {
        Greeting("Android")
    }
}