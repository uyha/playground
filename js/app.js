function commandName(name) {
  return { [name]: new RegExp(name) };
}

function commands(...names) {
  return Object.assign({}, ...names.map(commandName));
}

console.log(commands("asdf", "foreach"));
