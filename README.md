# Aplicação para o monitoramento de projetos

[![License](https://img.shields.io/badge/Licence-MIT-blue.svg)](LICENSE)

A aplicação foi desenvolvida utilizando o *framework WEB* [Django](https://docs.djangoproject.com/en/5.0/) (v5.0.6) com a linguagem Python na versão 3.12.3.

Pode-se utilizar a partir da versão do Python mais antiga com suporte de segurança (3.8). Consultar o [guia de versões](https://devguide.python.org/versions/).

O desenvolvimento foi realizado em ambiente linux, portanto, os comandos do arquivo `init.sh` são direcionados ao shell padrão de uma distribuição deste kernel.

Para Windows, o ambiente pode ser reproduzido via WSL2 ou pelo PowerShell utilizando os comandos equivalentes.

## Instruções

O projeto encontra-se na pasta `app`. Para criar o ambiente necessário, pode-se executar o arquivo `init.sh` ou seguir as instruções a seguir:

- Dentro da pasta `app`, utilizar o comando `sh init.sh` ou `./init.sh` (se a permissão `x`, de execução, estiver presente no arquivo).

Para dar permissão de execução ao arquivo para o usuário atual:

```{sh}
chmod u+x init.sh
```

1. Crie um ambiente virtual utilizando o módulo `venv`:

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

4. Gere os arquivos de tradução:

```{python}
python manage.py compilemessages
```

obs: Para alterar a linguagem da aplicação, deve-se atribuir à variável `LANGUAGE_CODE` (presente na linha `110` do arquivo `app/lab_control/settings.py`) o código da linguagem desejada. O padrão é `pt-br`, para inglês deve-se definí-la para `en-us`.

5. Inicie o servidor:

```{python}
python manage.py runserver 0.0.0.0:8000
```

### Observações

- O pacote `whitenoise` é utilizado para acesso aos arquivos estáticos, sem ele deve-se adicionar o argumento `--insecure` ao comando `runserver`, ou seja: `python manage.py runserver 0.0.0.0:8000 --insecure`.

## Aplicação em container

- Testado com a ferramenta podman.

Inicialmente, deve-se gerar a imagem a partir da aplicação, referenciando o arquivo Containerfile:

```{sh}
podman build -f Containerfile -t supervisor
```

Após a imagem ser gerada, utilizar o comando a seguir para iniciar o container com a aplicação:

```{sh}
podman run -d -p 8000:8000 --name labcontrol --restart=always localhost/supervisor
```
