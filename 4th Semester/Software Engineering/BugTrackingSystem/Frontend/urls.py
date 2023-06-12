from django.urls import path
from Frontend.views import index

urlpatterns = [
    path('', index),
    path('login', index)
]
