tests = [ 
    
    { # Test 1:
    'description': 'PINA: 0x00, 0x01, 0x00 => PORTB: 0x02',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 3 },
               {'inputs': [('PINA',0x01)], 'iterations': 3 },
               {'inputs': [('PINA',0x00)], 'iterations': 3 }
               ],
    'expected': [('PORTB',0x02)],
    },
     
]

watch = ['PINA', 'PORTB']
