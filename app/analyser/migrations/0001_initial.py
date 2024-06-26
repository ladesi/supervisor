# Generated by Django 4.0.6 on 2022-12-17 02:29

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Lab',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('device', models.TextField(blank=True, null=True, verbose_name='Device')),
                ('ip_addr', models.GenericIPAddressField(blank=True, null=True, verbose_name='device ip')),
            ],
            options={
                'verbose_name': 'Lab',
                'verbose_name_plural': 'Labs',
                'ordering': ['device'],
            },
        ),
    ]
