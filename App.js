import React from 'react';
import { StyleSheet, Button, Text, Image, Alert, View } from 'react-native';

export default function App() {
  return (
    <View style={styles.container}>
        <Text style={styles.homepageText}>Please Pair</Text>
      <Image style={styles.tinyLogo} source={require('./assets/glasses.png')}/>
        <Text style={styles.homepageText}>Your Glasses</Text>
    </View>

  );
}



const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#FAF',
    alignItems: 'center',
    justifyContent: 'center',
  },tinyLogo: {
    width: 300,
    height: 100,
  },homepageText: {
    color: 'white',
    fontWeight: "bold",
    fontSize: 50,
  },
});
