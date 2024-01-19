
import android.content.Intent
import android.net.Uri
import android.provider.Settings
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import com.google.accompanist.permissions.PermissionsRequired
import com.google.accompanist.permissions.rememberMultiplePermissionsState

@ExperimentalPermissionsApi
@Composable
fun Permissions(
    permissions: List<String>,
    rationaleText: String,
    dismissedText: String,
    content: @Composable () -> Unit = { }
) {
    val permissionsState = rememberMultiplePermissionsState(permissions = permissions)
    PermissionsRequired(
        multiplePermissionsState = permissionsState,
        permissionsNotGrantedContent = {
            PermissionsNotGranted(
                text = rationaleText,
                onRequestPermission = { permissionsState.launchMultiplePermissionRequest() }
            )
        },
        permissionsNotAvailableContent = {
            PermissionsNotAvailable(text = dismissedText)
        },
        content = content
    )
}

@Composable
private fun PermissionsNotGranted(
    text: String,
    onRequestPermission: () -> Unit
) {
    AlertDialog(
        onDismissRequest = { /* Don't */ },
        title = {
            Text(text = "Permission request")
        },
        text = {
            Text(text)
        },
        confirmButton = {
            Button(onClick = onRequestPermission) {
                Text("Ok")
            }
        }
    )
}

@Composable
private fun PermissionsNotAvailable(text: String) {
    val context = LocalContext.current
    Column(Modifier.fillMaxSize()) {
        Text(text)
        Spacer(modifier = Modifier.height(8.dp))
        Button(
            onClick = {
                context.startActivity(
                    Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS).apply {
                        data = Uri.fromParts("package", context.packageName, null)
                    }
                )
            }
        ) {
            Text("Open Settings")
        }
    }
}
