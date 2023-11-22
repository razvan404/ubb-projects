const acceptedQueryExtensions = ["StartsWith", "Contains", "EndsWith"];

const uncapitalize = (str: string) =>
  str.charAt(0).toLowerCase() + str.slice(1);

const toNumberIfNumber = (str: string): number | string => {
  const number = Number(str);
  return isNaN(number) ? str : number;
};

export const queryParamsToDict = (queryParams: { [key: string]: string }) => {
  const mappedObject: { [key: string]: any } = {};
  Object.entries(queryParams).map(([key, value]) => {
    for (const extension of acceptedQueryExtensions) {
      if (key.endsWith(extension)) {
        mappedObject[key.substring(0, key.length - extension.length)] = {
          [uncapitalize(extension)]: toNumberIfNumber(value),
        };
        return;
      }
    }
    mappedObject[key] = toNumberIfNumber(value);
  });
  return mappedObject;
};
