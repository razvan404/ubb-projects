export const logger =
  (tag: string, color: string = "red") =>
  (...args: any[]) =>
    console.log(
      `%c${tag}`,
      `color: ${color}; font-size: 14px; font-weight: bolder`,
      "-",
      ...args
    );
