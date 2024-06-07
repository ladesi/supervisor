from django.db import models
from django.conf import settings
from django.utils.translation import gettext_lazy as _

PROJECT_CHOICES = [
    ('analyser',_('Energy Meter')),
]

class Device(models.Model):
    db_table = '01_device'
    name = models.TextField(blank=False, null=False, verbose_name=_("Name"))
    project = models.CharField(blank=False, null=False, choices=PROJECT_CHOICES, default='analyser', max_length=15)
    ip_addr = models.GenericIPAddressField(blank=False, null=False, verbose_name=_("IP Address"))

    def __str__(self):
        return f'{self.name}'

    class Meta:
        ordering = ['name']
        verbose_name=_("Device")
        verbose_name_plural=_("Devices")
