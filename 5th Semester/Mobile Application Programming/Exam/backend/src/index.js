var koa = require('koa');
var app = module.exports = new koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({server});
const Router = require('koa-router');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');

app.use(bodyParser());

app.use(cors());

app.use(async function (ctx, next) {
  const start = new Date();
  await next();
  const ms = new Date() - start;
  console.log(`${ctx.method} ${ctx.url} - ${ms}ms`);
});

app.use(async (ctx, next) => {
  await new Promise(resolve => setTimeout(resolve, 3000));
  await next();
});

const getRandomInt = (min, max) => {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
};

const assets = [];
const names = ['u1', 'u2', 'u3'];

for (let i = 0; i < 10; i++) {
  assets.push({
    id: i,
    name: `a${i}`,
    takenBy: null,
    desiredBy: [names[getRandomInt(0, names.length)]],
  });
}

wss.on('connection', async ws => {
  console.log('on connection');
  await new Promise(resolve => setTimeout(resolve, 3000));
  ws.send(JSON.stringify(assets));
});

const broadcast = data =>
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      console.log('broadcast', data);
      client.send(JSON.stringify(data));
    }
  });

setInterval(() => {
  assets.push({
    id: assets.length + 1,
    name: `a${assets.length + 1}`,
    takenBy: null,
    desiredBy: [names[getRandomInt(0, names.length)]],
  });
  broadcast(assets[assets.length - 1]);
}, 10000);

const router = new Router();

router.patch('/asset/:id', ctx => {
  const id = ctx.params.id;
  if (typeof id !== 'undefined') {
    const index = assets.findIndex(obj => obj.id == id);
    if (index === -1) {
      ctx.response.body = {text: 'Invalid asset id'};
      ctx.response.status = 404;
    } else {
      Object.assign(assets[index], ctx.request.body);
      ctx.response.body = assets[index];
      ctx.response.status = 200;
      broadcast(assets[index]);
    }
  } else {
    ctx.response.body = {text: 'Id missing or invalid'};
    ctx.response.status = 404;
  }
});

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(3000);
