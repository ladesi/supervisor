from django import forms
from . models import Device

class IpRegisterForm(forms.ModelForm):

    class Meta:
        model = Device
        fields = ['ip_addr']
