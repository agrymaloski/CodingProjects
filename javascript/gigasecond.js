//this file accepts a date and returns the date 1 gigasecond later.

var millisecond;

export const gigasecond = (moment) => {
  millisecond = moment.getTime() +  Math.pow(10, 12);
  return new Date(millisecond);
};
