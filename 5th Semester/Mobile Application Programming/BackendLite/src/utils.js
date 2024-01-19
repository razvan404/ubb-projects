export const jwtConfig = { secret: "my-secret" };

export const exceptionHandler = async (ctx, next) => {
  try {
    return await next();
  } catch (err) {
    console.log(err);
    ctx.body = { message: err.message || "Unexpected error." };
    ctx.status = err.status || 500;
  }
};

export const timingLogger = async (ctx, next) => {
  const start = Date.now();
  await next();
  console.log(
    `Method: ${ctx.method} -- Route: ${ctx.url} => Status: ${
      ctx.response.status
    }, Response time: ${Date.now() - start}ms`
  );
};
