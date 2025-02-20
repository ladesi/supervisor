from django.contrib import admin
from django.contrib.auth import views as auth_views
from django.urls import path, include
from . import views

urlpatterns = [
    path('', views.home, name='home'),
    path('sobre/', views.about, name='home-about'),
    path('medidor/', include('analyser.urls')),
    path('admin/', admin.site.urls),
    path('logout/', views.UserLogoutView.as_view(http_method_names = ['get', 'post', 'options']), name="logout"),
]
