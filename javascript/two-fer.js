export const twoFer = (name) => {
  var string


  if (name === undefined){
    string = 'One for you, one for me.'
  } else{
    string = 'One for ' + name + 'one for me'
  }
  return string
};
