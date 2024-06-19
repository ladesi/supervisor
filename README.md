# Aplicação para o monitoramento de projetos

A aplicação foi desenvolvida utilizando o **framework WEB** Django, versão 5.0.6, com a linguagem Python na versão 3.13.3.

O desenvolvimento foi realizado em ambiente linux, portanto, os comandos são direcionados ao shell padrão de uma distribuição deste kernel.

Para Windows, o ambiente pode ser reproduzido via PowerShell ou a partir do WSL2.

## Instruções

O projeto encontra-se na pasta `app`. Para criar o ambiente necessário, pode-se executar o arquivo `init.sh` ou seguir as instruções a seguir:

- Dentro da pasta `app`, utilizar o comando `sh init.sh` ou `./init.sh` (se a permissão `x`, de execução, estiver presente no arquivo).

Para dar permissão de execução ao arquivo:

```{sh}
chmod u+x init.sh
```

1. Crie um ambiente virtual utilizando o módulo `env`:

```{python}
python -m venv venv
```

2. Ative o ambiente:

```{python}
source venv/bin/activate
```

3. Instale as dependências:

```{python}
pip install -r requirements.txt
```

4. Inicie o servidor:

```{python}
python manage.py runserver 0.0.0.0:8000 --insecure
```

### Observações

- A opção `--insecure` é utilizada para acesso aos arquivos estáticos.

- Sem ela, pode-se instalar o pacote `whitenoise`, mas, para esta aplicação, faz-se desnecessário.

Para compilar os arquivo de tradução:

```{python}
python manage.py compilemessages
```

## Container com Docker ou Podman

Inicialmente, deve-se gerar a imagem a partir da aplicação, referenciando o arquivo Containerfile:

```{sh}
podman build -f Containerfile -t supervisor
```

Após a imagem ser gerada, utilizar o comando a seguir para iniciar o container com a aplicação:

```{sh}
podman run -d -p 8000:8000 --name labcontrol --restart=always localhost/supervisor
```
