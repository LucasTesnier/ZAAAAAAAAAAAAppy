import 'dart:io';

import 'package:flutter/material.dart';
import 'dart:convert';
import 'dart:async';

late Socket socket;

late String response;

Map<int, Color> color =
{
  50:Color.fromRGBO(110,153,255, .1),
  100:Color.fromRGBO(110,153,255, .2),
  200:Color.fromRGBO(110,153,255, .3),
  300:Color.fromRGBO(110,153,255, .4),
  400:Color.fromRGBO(110,153,255, .5),
  500:Color.fromRGBO(110,153,255, .6),
  600:Color.fromRGBO(110,153,255, .7),
  700:Color.fromRGBO(110,153,255, .8),
  800:Color.fromRGBO(110,153,255, .9),
  900:Color.fromRGBO(110,153,255, 1),
};

Map<int, Color> colors =
{
  50:Color.fromRGBO(158,110,255, .1),
  100:Color.fromRGBO(158,110,255, .2),
  200:Color.fromRGBO(158,110,255, .3),
  300:Color.fromRGBO(158,110,255, .4),
  400:Color.fromRGBO(158,110,255, .5),
  500:Color.fromRGBO(158,110,255, .6),
  600:Color.fromRGBO(158,110,255, .7),
  700:Color.fromRGBO(158,110,255, .8),
  800:Color.fromRGBO(158,110,255, .9),
  900:Color.fromRGBO(158,110,255, 1),
};

void main() async {
  socket = await Socket.connect('192.168.122.1', 9996);

  socket.listen((List<int> event) {
    print(utf8.decode(event));
    response = utf8.decode(event);
  });

  socket.add(utf8.encode('/login FLUTTER\n\n'));

  await Future.delayed(Duration(seconds: 1));

  socket.add(utf8.encode('/get_density\n\n'));

  await Future.delayed(Duration(seconds: 1));

  runApp(MyApp(socket: socket));
}

class MyApp extends StatelessWidget {
  MyApp({Key? key, Socket? socket}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: MaterialColor(0XFF9e6eff, color),
        secondaryHeaderColor: MaterialColor(0XFF9e6eff, color),
        textTheme: TextTheme(bodyText1: TextStyle(color: MaterialColor(0XFF9e6eff, color)), bodyText2: TextStyle(color: MaterialColor(0XFF9e6eff, color)))

      ),
      home: MyHomePage(title: 'Zappy Pannel manager'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key? key, required this.title, Socket? socket}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  List<double> data = [0, 0, 0, 0, 0, 0, 0];

  void convert_response_to_data() {
    final first = response.split('[');

    final second = first[1].split(',');

    final third = second[6].split(']');
    print(second);
    data[0] = double.parse(second[0]);
    data[1] = double.parse(second[1]);
    data[2] = double.parse(second[2]);
    data[3] = double.parse(second[3]);
    data[4] = double.parse(second[4]);
    data[5] = double.parse(second[5]);
    data[6] = double.parse(third[0]);
  }

  String convert_data_to_response() {
    return "[${data[0]},${data[1]},${data[2]},${data[3]},"
        "${data[4]},${data[5]},${data[6]}]";
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
          child: Column(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: <Widget>[
          Image(image: AssetImage('assets/logo.png')),
          Text('Welcome to Zappy pannel manager'),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[0] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Food density : ' + data[0].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[0] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[1] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Linemate density : ' + data[1].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[1] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[2] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Deraumere density : ' + data[2].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[2] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[3] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Sibur density : ' + data[3].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[3] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[4] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Mendiane density : ' + data[4].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[4] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[5] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Phiras density : ' + data[5].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[5] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[6] -= 0.01;
                    });
                  },
                  child: Icon(Icons.remove)),
              Text('Thystame density : ' + data[6].toStringAsFixed(2)),
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      data[6] += 0.01;
                    });
                  },
                  child: Icon(Icons.add)),
            ],
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
            children: <Widget>[
              FloatingActionButton(
                  onPressed: () {
                    setState(() {
                      socket.add(utf8.encode('/push_density ${convert_data_to_response()}\n\n'));
                    });
                  },

                  child: Icon(Icons.network_cell)),
              Text('Send current data'),
                  Text('Reset generation data'),
                  FloatingActionButton(
                      onPressed: () async {
                        socket.add(utf8.encode('/get_density\n\n'));
                        await Future.delayed(Duration(seconds: 1));
                        convert_response_to_data();
                        setState(() {
                        });
                      },
                      child: Icon(Icons.reset_tv)),
            ],
          )
        ],
      )),
    );
  }
}
