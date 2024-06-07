from django.shortcuts import render, redirect, get_object_or_404
from .forms import IpRegisterForm
from django.contrib import messages
from .models import *

# globals
context = {}
DISP = "ESP-01"
ORG = "IFCE"

if ORG == 'IFCE':
    context["logo"] = "ifce"
    context["institute"] = "Instituto Federal de Educação, Ciência e Tecnologia do Ceará"
else:
    context["logo"] = "ufc"
    context["institute"] = "Universidade Federal do Ceará"

# home page
def home(request):
    if request.method == "POST":
        item = Device.objects.get(id=Device.objects.get(name=DISP).id)
        form = IpRegisterForm(request.POST or None, instance=item)
        if form.is_valid():
            form.save(commit=True)
            return redirect('analyser-home')
    else:
        form = IpRegisterForm()

    context["device"] = Device.objects.all()
    context["p_device"] = Device.objects.get(name=DISP)
    context["form"] = form

    return render(request, 'analyser/home.html',  context)

# table to show values from server
def table(request):
    context["p_device"] = Device.objects.get(name=DISP)

    return render(request, 'analyser/table.html', context)

# data test request
def data(request):
    return render(request, 'analyser/data.html')
