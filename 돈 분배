					if (restMoney == 0) {
						finalPrice = baseMoney
								+ (restMoney / (totalNumber * divisionNumber) * divisionNumber);
						str += finalPrice + "�� " + totalNumber + "��";

					} else {
						restPeople = restMoney / divisionNumber;
						finalPrice = baseMoney + divisionNumber;
						if (restMoney % divisionNumber == 0) {
							str += finalPrice + "�� " + restPeople + "��\n";
							str += (baseMoney + (restMoney % divisionNumber))
									+ "�� " + (totalNumber - restPeople) + "��";
						} else {
							if (restPeople != 0)
								str += finalPrice + "�� " + restPeople + "��\n";
							if (totalNumber - restPeople - 1 != 0)
								str += baseMoney + "�� "
										+ (totalNumber - restPeople - 1)
										+ "��\n";
							str += (baseMoney + (restMoney % divisionNumber))
									+ "�� 1��";
							// }

						}
					}
