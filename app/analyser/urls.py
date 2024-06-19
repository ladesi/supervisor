from django.contrib import admin
from django.urls import path, include
from . import views

urlpatterns = [
    path('', views.home, name='analyser-home'),
    path('data/', views.data, name='analyser-data'),
    path('table/', views.table, name='analyser-table'),
]
