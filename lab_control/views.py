from django.shortcuts import render, redirect, get_object_or_404
from django.contrib import messages
from analyser.views import context


def home(request):
    return render(request, 'home.html', context)

def about(request):
    return render(request, 'about.html', context)
