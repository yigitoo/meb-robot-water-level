from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, FileResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates

from fastapi.middleware.cors import CORSMiddleware


import json
import os

app = FastAPI()

origins = [
    "http://localhost.tiangolo.com",
    "https://localhost.tiangolo.com",
    "http://localhost",
    "http://localhost:8080",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


HTTP_TYPE = 'http'
HOST = '0.0.0.0'
PORT = 8080

app.mount('/static', StaticFiles(directory='static'), name='static')
templates = Jinja2Templates(directory='templates')

@app.get('/static/index.js')
async def index_js():
    return FileResponse(
        os.path.join(
            os.getcwd() +
            'static' + '/index.js'
        )
    )

@app.post('/data')
async def data_retrieving(request: Request):
    data = await request.json()
    with open('data.json', 'w') as file:
        file.write(
            json.dumps(data, indent=4)
        )

    return {
        "state": "Data successfully changed",
        "success": "true",
        "data": data
    }

@app.get('/', response_class=HTMLResponse)
async def index(request: Request):
    return templates.TemplateResponse(
        request=request, name='index.html'
    )

@app.get('/getData')
async def get_data():
    try:
        file = open('data.json', 'r')
        data = json.load(file)
        file.close()

        # dictionary comprehension
        return {
            key: value
            for (key, value)
            in data.items()
        } | {"success": "true"}

    except:
        return {
            'state': 'Cannot access to data for now.',
            'success': "false"
        }

if __name__ == '__main__':
    import uvicorn
    uvicorn.run(app, host=HOST, port=PORT)
