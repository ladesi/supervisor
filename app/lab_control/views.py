from django.shortcuts import render, redirect, get_object_or_404
from django.contrib import messages
from analyser.views import context
from django.contrib.auth import logout
from django.contrib.auth.views import LogoutView


def home(request):
    return render(request, 'home.html', context)


def about(request):
    return render(request, 'about.html', context)


class UserLogoutView(LogoutView):
    def get(self, request):
        logout(request)
        return redirect('home')
