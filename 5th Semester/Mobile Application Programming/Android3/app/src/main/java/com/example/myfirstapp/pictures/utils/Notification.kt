package com.example.myfirstapp.pictures.utils

import android.app.NotificationChannel
import android.app.NotificationManager
import android.content.Context
import android.content.pm.PackageManager
import android.os.Build
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import androidx.core.app.NotificationManagerCompat
import com.example.myfirstapp.R

fun createNotificationChannel(channelId: String, context: Context) {
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
        val name = "MyTestChannel"
        val descriptionText = "My important test channel"
        val importance = NotificationManager.IMPORTANCE_DEFAULT
        val channel = NotificationChannel(channelId, name, importance).apply {
            description = descriptionText
        }

        val notificationManager: NotificationManager =
            context.getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager
        notificationManager.createNotificationChannel(channel)
    }
}

// shows notification with a title and one-line content text
fun showSimpleNotification(
    context: Context,
    channelId: String,
    notificationId: Int,
    textTitle: String,
    textContent: String,
    priority: Int = NotificationCompat.PRIORITY_DEFAULT
) {
    val builder = NotificationCompat.Builder(context, channelId)
        .setSmallIcon(R.drawable.ic_edit_location)
        .setContentTitle(textTitle)
        .setContentText(textContent)
        .setPriority(priority)

    with(NotificationManagerCompat.from(context)) {
        if (ActivityCompat.checkSelfPermission(
                context,
                "android.permission.POST_NOTIFICATIONS"
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
        notify(notificationId, builder.build())
    }
}

//// shows a simple notification with a tap action to show an activity
//fun showSimpleNotificationWithTapAction(
//    context: Context,
//    channelId: String,
//    notificationId: Int,
//    textTitle: String,
//    textContent: String,
//    priority: Int = NotificationCompat.PRIORITY_DEFAULT
//) {
//    val intent = Intent(context, MainActivity::class.java).apply {
//        flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
//    }
//
//    val pendingIntent: PendingIntent = PendingIntent.getActivity(context, 0, intent,
//        PendingIntent.FLAG_IMMUTABLE)
//
//    val builder = NotificationCompat.Builder(context, channelId)
//        .setSmallIcon(R.drawable.ic_edit_location)
//        .setContentTitle(textTitle)
//        .setContentText(textContent)
//        .setPriority(priority)
//        .setContentIntent(pendingIntent)
//        .setAutoCancel(true)
//
//    with(NotificationManagerCompat.from(context)) {
//        notify(notificationId, builder.build())
//    }
//}
