from django.contrib import admin
from . models import *
from django.http import HttpResponse

@admin.register(Device)
class GroupAdmin(admin.ModelAdmin):
    list_display = ("name",)
    list_filter = ("ip_addr",)
