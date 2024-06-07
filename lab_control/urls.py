from django.contrib import admin
from django.urls import path, include
from . import views

urlpatterns = [
    path('', views.home, name='home'),
    path('sobre/', views.about, name='home-about'),
    path('medidor/', include('analyser.urls')),
    path('admin/', admin.site.urls),
]
