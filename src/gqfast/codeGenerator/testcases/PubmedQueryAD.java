package gqfast.codeGenerator.testcases;

import gqfast.codeGenerator.AggregationOperator;
import gqfast.codeGenerator.CodeGenerator;
import gqfast.codeGenerator.JoinOperator;
import gqfast.codeGenerator.Operator;
import gqfast.codeGenerator.ThreadingOperator;
import gqfast.codeGenerator.IntersectionOperator;
import gqfast.global.Alias;
import gqfast.global.MetaData;
import gqfast.global.MetaIndex;
import gqfast.global.MetaQuery;

import java.util.ArrayList;
import java.util.List;

public class PubmedQueryAD {

	private static void initQ3Queries(MetaData metadata, String queryName, int numThreads) {

		List<Alias> aliases = new ArrayList<Alias>();
		
		Alias alias0 = new Alias(0, "doc1", metadata.getIndexList().get(0));
		Alias alias1 = new Alias(1, "author1", metadata.getIndexList().get(1));
		
		aliases.add(alias0);
		aliases.add(alias1);
		
		// public MetaQuery(int queryID, String queryName, int numThreads,
		// int numBuffers, int bufferPoolSize, List<String> aliases)
		MetaQuery q3Optimal = new MetaQuery(0, queryName, numThreads, 2, aliases);
				
		metadata.getQueryList().add(q3Optimal);
		metadata.setCurrentQueryID(metadata.getQueryList().size()-1);
		
	}
	
	private static void initQ3Indexes(MetaData metadata, int encodingType) {
		
		// DT2
		int indexID = 3;
		int numColumns = 2;
		List<Integer> columnEncodingsList3 = new ArrayList<Integer>();
		columnEncodingsList3.add(encodingType);
		columnEncodingsList3.add(encodingType);
		
		List<Integer >columnEncodedByteSizesList3 = new ArrayList<Integer>();
		columnEncodedByteSizesList3.add(MetaData.BYTES_4);
		columnEncodedByteSizesList3.add(MetaData.BYTES_1);
		
		MetaIndex DT2 = new MetaIndex(0, indexID, numColumns, MetaData.BYTES_4, columnEncodingsList3, columnEncodedByteSizesList3);
		metadata.getIndexList().add(DT2);
		
		// DA2
		indexID = 4;
		numColumns = 1;
		List<Integer> columnEncodingsList4 = new ArrayList<Integer>();
		columnEncodingsList4.add(encodingType);
		List<Integer> columnEncodedByteSizesList4 = new ArrayList<Integer>();
		columnEncodedByteSizesList4.add(MetaData.BYTES_4);
		
		MetaIndex DA2 = new MetaIndex(1, indexID, numColumns, MetaData.BYTES_4, columnEncodingsList4, columnEncodedByteSizesList4);
		metadata.getIndexList().add(DA2);
		

	}
	
	
	private static void initQ3Indexes(MetaData metadata) {

		// DT2
		int indexID = 3;
		int numColumns = 2;
		List<Integer> columnEncodingsList3 = new ArrayList<Integer>();
		columnEncodingsList3.add(MetaData.ENCODING_BB);
		columnEncodingsList3.add(MetaData.ENCODING_HUFFMAN);
		
		List<Integer >columnEncodedByteSizesList3 = new ArrayList<Integer>();
		columnEncodedByteSizesList3.add(MetaData.BYTES_4);
		columnEncodedByteSizesList3.add(MetaData.BYTES_1);
		
		MetaIndex DT2 = new MetaIndex(0, indexID, numColumns, MetaData.BYTES_4, columnEncodingsList3, columnEncodedByteSizesList3);
		metadata.getIndexList().add(DT2);
		
		
		// DA2
		indexID = 4;
		numColumns = 1;
		List<Integer> columnEncodingsList4 = new ArrayList<Integer>();
		columnEncodingsList4.add(MetaData.ENCODING_BCA);
		List<Integer> columnEncodedByteSizesList4 = new ArrayList<Integer>();
		columnEncodedByteSizesList4.add(MetaData.BYTES_4);
		
		MetaIndex DA2 = new MetaIndex(1, indexID, numColumns, MetaData.BYTES_4, columnEncodingsList4, columnEncodedByteSizesList4);
		metadata.getIndexList().add(DA2);

	}
	private static void initQ3Operators(List<Operator> operators, MetaQuery query, List<Integer> selections) {
	
		List<Alias> aliases = query.getAliases();
	
		
		List<Alias> intersectionAliases = new ArrayList<Alias>();
		intersectionAliases.add(aliases.get(0));
		intersectionAliases.add(aliases.get(0));
		
		List<Integer> columnIDs = new ArrayList<Integer>();
		columnIDs.add(0);
		columnIDs.add(0);
		
		//public IntersectionOperator(boolean bitwiseFlag, List<Alias> aliases, 
			//	List<Integer> columnIDs, List<Integer> selections) {
		Operator intersectionOp = new IntersectionOperator(false, intersectionAliases, columnIDs, selections);
		operators.add(intersectionOp);	
		
		List<Integer> column1IDs = new ArrayList<Integer>();
		column1IDs.add(0);
		// JoinOperator(int indexID, boolean entityFlag, List<Integer> columnIDs,  int alias, int loopColumn, int drivingAliasID, int drivingAliasColumn)
		Operator join1 = new JoinOperator(true, column1IDs, aliases.get(1), aliases.get(0), 0);
		
		operators.add(join1);
			
		int aggregationindexID = 4;
		
		String aggString = "1";
		
		List<Alias> aggAliasList = new ArrayList<Alias>();
		List<Integer> aggOpColList = new ArrayList<Integer>();
		
		/*public AggregationOperator(int indexID, 
				int dataType, String aggregationString, 
				List<Integer> aggregationVariablesOperators, List<Integer> aggregationVariablesColumns, int drivingAlias, 
				int drivingAliasColumn, int drivingOperator, int drivingAliasIndexID) {*/
		
		Operator agg = new AggregationOperator(aggregationindexID, 
				AggregationOperator.AGGREGATION_INT, aggString, aggAliasList, aggOpColList, aliases.get(1), 0);
	
		operators.add(agg);
	}
	
	private static void initQ3OperatorsThreaded(List<Operator> operators, MetaQuery query, List<Integer> selections) {
		
		List<Alias> aliases = query.getAliases();
	
		
		List<Alias> intersectionAliases = new ArrayList<Alias>();
		intersectionAliases.add(aliases.get(0));
		intersectionAliases.add(aliases.get(0));
		
		List<Integer> columnIDs = new ArrayList<Integer>();
		columnIDs.add(0);
		columnIDs.add(0);
		
		//public IntersectionOperator(boolean bitwiseFlag, List<Alias> aliases, 
			//	List<Integer> columnIDs, List<Integer> selections) {
		Operator intersectionOp = new IntersectionOperator(false, intersectionAliases, columnIDs, selections);
		operators.add(intersectionOp);		
		
		Operator threadingOp = new ThreadingOperator(aliases.get(0), true);
		operators.add(threadingOp);
		
		List<Integer> column1IDs = new ArrayList<Integer>();
		column1IDs.add(0);
		// JoinOperator(int indexID, boolean entityFlag, List<Integer> columnIDs,  int alias, int loopColumn, int drivingAliasID, int drivingAliasColumn)
		Operator join1 = new JoinOperator(true, column1IDs, aliases.get(1), aliases.get(0), 0);
		
		operators.add(join1);
			
		int aggregationindexID = 4;
		
		String aggString = "1";
		
		List<Alias> aggAliasList = new ArrayList<Alias>();
		List<Integer> aggOpColList = new ArrayList<Integer>();
		
		/*public AggregationOperator(int indexID, 
				int dataType, String aggregationString, 
				List<Integer> aggregationVariablesOperators, List<Integer> aggregationVariablesColumns, int drivingAlias, 
				int drivingAliasColumn, int drivingOperator, int drivingAliasIndexID) {*/
		
		Operator agg = new AggregationOperator(aggregationindexID, 
				AggregationOperator.AGGREGATION_INT, aggString, aggAliasList, aggOpColList, aliases.get(1), 0);
	
		operators.add(agg);
	
	}
	
	private static void runQ3(String queryName, int numThreads, List<Integer> selections, int encoding) {
		List<Operator> operators = new ArrayList<Operator>();
		MetaData metadata = new MetaData();
		
		initQ3Indexes(metadata, encoding);
		initQ3Queries(metadata, queryName, numThreads);
		MetaQuery query = metadata.getQueryList().get(metadata.getCurrentQueryID());
		
		
		if (numThreads > 1) {
			initQ3OperatorsThreaded(operators, query, selections);
		}
		else {
			initQ3Operators(operators, query, selections);
		}
		CodeGenerator.generateCode(operators, metadata);
	}
	

	private static void runQ3(String queryName, int numThreads, List<Integer> selections, boolean b) {
		List<Operator> operators = new ArrayList<Operator>();
		MetaData metadata = new MetaData();
		initQ3Indexes(metadata);
		initQ3Queries(metadata, queryName, numThreads);
		MetaQuery query = metadata.getQueryList().get(metadata.getCurrentQueryID());
		if (numThreads > 1) {
			initQ3OperatorsThreaded(operators, query, selections);
		}
		else {
			initQ3Operators(operators, query, selections);
		}
		CodeGenerator.generateCode(operators, metadata);
	}
	
	public static void main(String[] args) {
		List<Integer> selections = new ArrayList<Integer>();
		selections.add(1);
		selections.add(2);
		//Q2 Optimal
		runQ3("test_pubmed_q3_opt", 1, selections, true);
		runQ3("test_pubmed_q3_opt_threaded", 4, selections, true);
		
		// Q2 UA
		runQ3("test_pubmed_q3_array", 1, selections, MetaData.ENCODING_UA);
		runQ3("test_pubmed_q3_array_threaded", 4, selections, MetaData.ENCODING_UA);
		
		
		// Q2 BCA
		runQ3("test_pubmed_q3_bca", 1, selections, MetaData.ENCODING_BCA);
		runQ3("test_pubmed_q3_bca_threaded", 4, selections, MetaData.ENCODING_BCA);
				
		// Q2 Huffman
		runQ3("test_pubmed_q3_huffman", 1, selections, MetaData.ENCODING_HUFFMAN);
		runQ3("test_pubmed_q3_huffman_threaded", 4, selections, MetaData.ENCODING_HUFFMAN);
		
		
		
	}
	
	
	
	
}